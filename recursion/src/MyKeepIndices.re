
//let words = [|"cow", "aardvark", "squirrel", "fish", "snake", "capybara"|];
//let expected = [|0, 3, 4|];

let keepIndices = (words: array(string), pred) : array(int) => {
  let rec helper = (acc, ws: array(string), idx: int) : array(int) => {
    switch(ws) {
      | [||] => acc
      | _ => {
        let first = ws[0];
        let tail = Array.sub(ws, 1, Array.length(ws) -1);
        if(pred(first)) {
          helper(Array.concat([acc, [|idx|]]), tail, idx + 1);
        } else {
          helper(acc, tail, idx+1);
        }
      }
    }
  };

  helper([||], words, 0);
}; 


//Js.log(keepIndices(words, x => { Js.String.length(x) < 6;}));

// This version is very slow compared to the one from WithHelper.re:
/*
takeshi:collections-app$ node src/TestSpeed.bs.js 
MyKeepIndices.keepIndices() average time in msec: 1.508
WithHelper.keepIndices() average time in msec:    0.039
takeshi:collections-app$ 
takeshi:collections-app$ node src/TestSpeed.bs.js 
MyKeepIndices.keepIndices() average time in msec: 1.516
WithHelper.keepIndices() average time in msec:    0.039
takeshi:collections-app$ 
takeshi:collections-app$ node src/TestSpeed.bs.js 
MyKeepIndices.keepIndices() average time in msec: 1.522
WithHelper.keepIndices() average time in msec:    0.051
takeshi:collections-app$ 
takeshi:collections-app$ node src/TestSpeed.bs.js 
MyKeepIndices.keepIndices() average time in msec: 1.504
WithHelper.keepIndices() average time in msec:    0.041
takeshi:collections-app$ 
takeshi:collections-app$ node src/TestSpeed.bs.js 
MyKeepIndices.keepIndices() average time in msec: 1.479
WithHelper.keepIndices() average time in msec:    0.05
*/

