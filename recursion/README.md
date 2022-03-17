# Tried to writeh my own keepIndices function but got bad performance:
```
takeshi:recursion$ node src/TestSpeed.bs.js 
MyKeepIndices.keepIndices() average time in msec: 1.501
WithHelper.keepIndices() average time in msec:    0.039

takeshi:recursion$ node src/TestSpeed.bs.js 
MyKeepIndices.keepIndices() average time in msec: 1.528
WithHelper.keepIndices() average time in msec:    0.039

takeshi:recursion$ node src/TestSpeed.bs.js 
MyKeepIndices.keepIndices() average time in msec: 1.508
WithHelper.keepIndices() average time in msec:    0.048

takeshi:recursion$ node src/TestSpeed.bs.js 
MyKeepIndices.keepIndices() average time in msec: 1.509
WithHelper.keepIndices() average time in msec:    0.041
takeshi:recursion$ 
```
