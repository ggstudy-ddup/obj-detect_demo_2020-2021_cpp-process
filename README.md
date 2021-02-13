# Chinese Academy of Science Project Demonstration - Invoking of TorchScript module

This is a program that could give classification prediction by invoking a given trained TorchScript module.
Planned to run as an independent process, which will only load the module once.

Now it is fit for Node.js program to load as a child process, communicate with reading/writing its standard output/input.

---

## Compile Environment

| Library   | Architecture  | Version   |
| :---      | :---:         | :---:     |
| LibTorch  | x64 for CPU   | 1.7.1     |
| jsoncpp   | x64           | 1.9.4     |

## Usage

Create as a child process
```javascript
var child_process = require('child_process');
var child = child_process.spawn('./invoke.exe', ['./assets/module.pt']); 
```

Read from stdout of the child process
```javascript
child.stdout.on('data', function (data) {
    console.log(data.toString());
});
```

Write to stdin of the child process
```javascript
child.stdin.write("Msg from Node.js!\n");
child.stdin.write("Msg2 from Node.js!\n");
```

---

## Communicate Protocol

Use Json to communicate. Every thing sended or received is Json format string.

To send a Json string stream to the invoking process, the stream should not
contain ***MORE THAN ONE*** line break (`'\n'`). You should have ***ONE AND ONLY ONE***
`'\n'` at the end of the message in order to flush the stream correctly.

The format should be restricted like this:
```json
{
    "type" : "XXX",
    "data" : "XXX"
}
```
`"XXX"` means the value you're trying to send.

The value of `"data"` is not restricted to any specific type. It could also be
an array, etc..

Of course, the Json stream should be like this when sending the message:
```json
{ "type" : "XXX", "data" : "XXX" }
```
