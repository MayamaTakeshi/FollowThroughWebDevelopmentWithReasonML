let takeWhile = (items: list('a), f: 'a => bool) : list('a) => {
    let rec helper = (acc, items) => {
        switch(items) {
         | [] => acc
         | [x, ..._] when ! f(x) => acc
         | [x, ...xs] => helper([x, ...acc], xs)
        } 
    };

    let temp = helper([], items);
    Belt.List.reverse(temp);
};

let rec dropWhile = (items: list('a), f: 'a => bool) : list('a) => {
    switch(items) {
     | [] => items
     | [x, ...xs] when f(x) => dropWhile(xs, f)
     | _ => items
    }
};

let data = [2, 6, 42, 5, 7, 20, 51];
let isEven = ( n ) => { ( n mod 2) == 0 };

let taken = takeWhile(data, isEven );
Js.log(taken);
Js.log(taken == [2, 6, 42]);

let dropped = dropWhile(data, isEven );
Js.log(dropped)
Js.log(dropped == [5, 7, 20, 51]);
Js.log(List.nth(dropped, 3) == 51);

