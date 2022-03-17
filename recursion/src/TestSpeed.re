let rec repeatTest = (n: int, accumulatedTime: float, f): float => {
  switch(n) {
   | 0 => accumulatedTime
   | _ => {
     let startTime = Js.Date.now();
     let _ = f();
     let endTime = Js.Date.now();
     repeatTest(n - 1, accumulatedTime +. (endTime -. startTime), f)
    }
   }
};

let words = Array.make(1000, "aardvark")
let repetitions = 1000

let myfu = () => {
    let _ = MyKeepIndices.keepIndices(words, x => { Js.String.length(x) < 6;})
}

let totalTime = repeatTest(repetitions, 0.0, myfu);

Js.log2("MyKeepIndices.keepIndices() average time in msec:", totalTime /. float_of_int(repetitions));

let myfu2 = () => {
    let _ = WithHelper.keepIndices(words, x => { Js.String.length(x) < 6;})
}

let totalTime = repeatTest(repetitions, 0.0, myfu2);
Js.log2("WithHelper.keepIndices() average time in msec:   ", totalTime /. float_of_int(repetitions));

