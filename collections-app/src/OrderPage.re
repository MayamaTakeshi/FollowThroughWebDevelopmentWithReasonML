module D = Webapi.Dom;
module Doc = Webapi.Dom.Document;
module Elem = Webapi.Dom.Element;

let commaSplit = (s: string) : array(string) => {
 // let pattern = [%re "/\\s*,\\s*/"];
 let pattern = [%re {|/\s*,\s*/|}]; // alternative syntax to not require escaping backslashes.

 Js.String.splitByRe(pattern, s) ->
  Belt.Array.map((item) => {
    Belt.Option.getWithDefault(item, "")
  })
};

type order = (int, ShirtSize.t);

type resultOrder = Belt.Result.t(order, string)

let orderFromCaptures = (optCaptures: option(array(string)), input: string): resultOrder => {
 switch(optCaptures) {
  |Some(captures) => {
    switch(ShirtSize.fromString(captures[2])) {
     |Some(size) => Belt.Result.Ok((int_of_string(captures[1]), size))
     |None => Belt.Result.Error(input)
    }
  }
  |None => Belt.Result.Error(input)
 }
};

let toOrder = (input: string) : resultOrder => {
  let pattern = [%re "/(\\d{1,4})\\s*@?\\s*(S|M|X{0,4}L)/"];
  Js.String.toUpperCase(input)
  -> Js.String.match(pattern,_)
  -> orderFromCaptures(input)
};

let calculateTotalShirts = (orders: array(resultOrder)): int => {
 let adder = (accumulator: int, resOrder: resultOrder) => {
  switch (resOrder) {
   | Belt.Result.Ok((n, _)) => accumulator + n
   | _ => accumulator
  }
 };
 Belt.Array.reduce(orders, 0, adder);
};

let orderPrice = ((n, size): order): float => {
 float_of_int(n) *. ShirtSize.price(size);
};

let addOrderTotal = ((totalShirts, totalPrice) as current, orderResult) => {
 switch(orderResult) {
  | Belt.Result.Ok((n, _) as order) => (
    totalShirts + n,
    totalPrice +. orderPrice(order)
   )
  | _ => current
 }
};

let calculateTotals = (orders: array(resultOrder)): (int, float) => {
  Belt.Array.reduce(orders, (0, 0.0), addOrderTotal);
};

let createRow = (anOrder: resultOrder): string => {
 switch(anOrder) {
  | Belt.Result.Ok((n, size)) => {
     let totalPrice = 
      Js.Float.toFixedWithPrecision(orderPrice((n, size)), ~digits=2);
     let sizeStr = ShirtSize.toString(size);
     {j|<tr><td class="right">$n</td>
        <td class="center">$sizeStr</td>
        <td class="right">\$$totalPrice</td></tr>\n|j}
    }
  | Belt.Result.Error(s) =>
     {j|<tr><td colspan="3">Bad input $s</td></tr>\n|j}
 }
};

let createTable = (orderArray: array(resultOrder)): string => {
  let tableBody = Belt.Array.reduce(orderArray, "",
    (accumulator, item) => accumulator ++ createRow(item));

  {j|
  <table>
   <thead>
     <tr><th>Quantity</th><th>Size</th><th>Price</th>
   </thead>
   <tbody>
    $tableBody
    <tbody>
   </table>
  |j};
}; 

let getValue = (element: option(Elem.t)): option(string) => {
  element
  -> Belt.Option.map(Elem.unsafeAsHtmlElement)
  -> Belt.Option.map(D.HtmlElement.value);
};

let setInnerHTML = (id: string, htmlString: string) => {
  Doc.getElementById(D.document, id)
  -> Belt.Option.map(Elem.setInnerHTML(_, htmlString))
};

let setInnerText = (id: string, textString: string) => {
  Doc.getElementById(D.document, id)
  -> Belt.Option.map(Elem.setInnerText(_, textString))
};

let calculate = (_: Dom.event): unit => {
 switch(getValue(Doc.getElementById(D.document, "orders"))) {
  | Some(str) => {
     let orderArray = commaSplit(str) ->
       Belt.Array.keep((item) => {item !== ""}) ->
       Belt.Array.map(toOrder);

     let (nShirts, grandTotal) = calculateTotals(orderArray);
     let priceString = Js.Float.toFixedWithPrecision(grandTotal, ~digits=2);
     let _ = setInnerHTML("table", createTable(orderArray));
     let _ = setInnerText("totalShirts", string_of_int(nShirts));
     let _ = setInnerText("totalPrice", priceString);
     ()
  }
  | None => ()
 }
};

let calcButton = Doc.getElementById(D.document, "calculate");
switch (calcButton) {
 | Some(element) =>
    D.EventTarget.addEventListener(
      D.Element.asEventTarget(element), "click", calculate)
 | None => ()
};

