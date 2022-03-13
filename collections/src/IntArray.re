
let items = [|10,11,12,13,14,15,16|];
Js.log(items);

let more = [|17, 18, 19|];
let joined = Belt.Array.concat(items, more);

