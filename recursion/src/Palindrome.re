
/* this version is very slow with a string with 50000 chars */
let rec isPalindromeVerySlow = (s: string): bool => {
    let len = String.length(s)
    if(len <= 1) {
        true
    } else if(String.get(s,0) != String.get(s, len-1)) {
        false
    } else {
        isPalindromeVerySlow(String.sub(s, 1, len-2))
    }
};

let rec isPalindrome = (s : string) : bool => {
    let len = Js.String.length (s);
    if (len <= 1) {
        true;
    } else if (Js.String.get(s , 0) != Js.String.get(s ,len - 1)) {
        false;
    } else {
        isPalindrome(Js.String.slice(~from = 1, ~to_ = len - 1, s ));
    }
};


Js.log ( isPalindrome ( "civic" )); /* output: true */
Js.log ( isPalindrome ( "deed" )); /* output: true */
Js.log ( isPalindrome ( "runner" )); /* output: false */


let repeatWithReduce = (s: string, n: int) : string => {
  Belt.Array.reduce(Belt.Array.range(0, n- 1), "",
    (accumulator: string, _item: int) => { accumulator ++ s});
};

let rec repeatRec = (s: string, accumulator: string, n: int) : string => {
  switch(n) {
    | 0 => accumulator 
    | _ => repeatRec(s, accumulator ++ s, n - 1)
  }
};

Js.log(repeatRec("ha", "", 4));

let repeat = (s: string, n: int) => {
  let rec repeatHelper = (acc: string, counter: int) => {
    switch(counter) {
     | 0 => acc
     | _ => repeatHelper(acc ++ s, counter -1)
    }
  };
  repeatHelper("", n);
};
Js.log(repeat("ha", 4));

let testString = repeat("a", 50000);
let rec repeatTest = (n: int, accumulatedTime: float): float => {
  switch(n) {
   | 0 => accumulatedTime
   | _ => {
     let startTime = Js.Date.now();
     let _ = isPalindrome(testString);
     let endTime = Js.Date.now();
     repeatTest(n - 1, accumulatedTime +. (endTime -. startTime))
    }
   }
};
let repetitions = 1000
let totalTime = repeatTest(repetitions, 0.0);
Js.log2("Average time in msec:", totalTime /. float_of_int(repetitions));
