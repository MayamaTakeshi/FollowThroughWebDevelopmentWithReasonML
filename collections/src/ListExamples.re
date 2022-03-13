let items = [10, 11, 12, 13, 14, 15, 16];

let sqrtPlusOne = (x) => { sqrt(float_of_int(x) +. 1.0) };
let rootsList = Belt.List.makeBy(5, sqrtPlusOne);
let rootsArray = Belt.Array.makeBy(5, sqrtPlusOne);
Js.log2("rootsList:", rootsList);
Js.log2("rootsArray:", rootsArray);
