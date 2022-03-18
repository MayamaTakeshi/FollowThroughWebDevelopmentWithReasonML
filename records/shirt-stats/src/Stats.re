module ColorComparator = 

Belt.Id.MakeComparable({
 type t = Shirts.Color.t;

 let cmp = compare;
});

type colorMapType = Belt.Map.t(Shirts.Color.t, int, ColorComparator.identity);

let colorReducer = (accumulatedMap: colorMapType, item: Shirts.order):
  colorMapType => {
    let n = Belt.Map.getWithDefault(accumulatedMap, item.color, 0);
    Belt.Map.set(accumulatedMap, item.color, n + item.quantity);
};

let printStatistics = (orders: list(Shirts.order)) : unit => {
 let colorDistribution =
  Belt.List.reduce(
    orders,
    Belt.Map.make(~id=(module ColorComparator)),
    colorReducer);

  Js.log2("Color", "Quantity");
  Belt.Map.forEach(colorDistribution,
   (key, value) => Js.log2(Shirts.Color.toString(key), value)
  );
};
  
let map2 = (optX, optY, f) => {
 switch(optX, optY) {
  | (Some(x), Some(y)) => Some(f(x,y))
  | (_, _) => None
 }
};

let lineReducer = (acc: list(Shirts.order), line: string) : list(Shirts.order) => {
 let items = Js.String.split(",", line);

 if(Belt.Array.length(items) != 7) {
  acc;
 } else {
  let initial : option(Shirts.order) =
    Some({
     quantity: 0,
     size: Small,
     sleeve: Short,
     color: White,
     pattern: Solid,
     cuff: Button,
     collar: Straight,
  });

  let orderRecord = initial
    -> map2(Belt.Int.fromString(items[0]),
        (result, n) => {...result, quantity: n})
    -> map2(Shirts.Size.fromString(items[1]),
        (result, sz) => {...result, size: sz})
    -> map2(Shirts.Color.fromString(items[2]),
        (result, c) => {...result, color: c})
    -> map2(Shirts.Pattern.fromString(items[3]),
        (result, pat) => {...result, pattern: pat})
    -> map2(Shirts.Collar.fromString(items[4]),
        (result, coll) => {...result, collar: coll})
    -> map2(Shirts.Sleeve.fromString(items[5]),
        (result, sleeve) => {...result, sleeve: sleeve})
    -> map2(Shirts.Cuff.fromString(items[6]),
        (result, cuff) => {...result, cuff: cuff});

  switch(orderRecord) {
   | Some(result) => [result, ...acc]
   | None => acc
  }
 }
};

  
let processFile = (inFileName: string): unit => {
 let fileContents = Node.Fs.readFileAsUtf8Sync(inFileName);
 let lines = Js.String.split("\n", fileContents) ->
  Belt.Array.sliceToEnd(1); /* get rid of header lines */

 let orders = Belt.Array.reduce(lines, [], lineReducer);

 printStatistics(orders);
};

let nodeArg = Belt.Array.get(Node.Process.argv, 0);
let progArg = Belt.Array.get(Node.Process.argv, 1);
let fileArg = Belt.Array.get(Node.Process.argv, 2);

switch(nodeArg, progArg, fileArg) {
 |(_, _, Some(inFileName)) => processFile(inFileName)
 |(Some(node), Some(prog),_) =>
   Js.log("Usage: " ++ node ++ " " ++ prog ++ " inputfile.csv")
 |(_,_,_) =>
   Js.log("How did you get here without NodeJS or a program to run?")
};


