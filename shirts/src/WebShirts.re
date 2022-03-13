module D = Webapi.Dom;
module Doc = Webapi.Dom.Document;
module Elem = Webapi.Dom.Element;

Js.log("Started!");


type shirtSize = 
 | Small
 | Medium
 | Large
 | XLarge(int);

let price = (size: option(shirtSize)) : option(float) => {
  switch(size) {
    | Some(Small) => Some(11.00)
    | Some(Medium) => Some(12.50)
    | Some(Large) => Some(14.00)
    | Some(XLarge(n)) => Some(16.0 +. (float_of_int(n-1) *. 0.50))
    | None => None
  };
};

let stringOfShirtSize = (size: shirtSize) : string => {
  switch(size) {
    | Small => "S"
    | Medium => "M"
    | Large => "L"
    | XLarge(n) => String.make(n, 'X') ++ "L"
  };
};

let shirtSizeOfString = (str: string) : option(shirtSize) => {
  switch (str) {
   | "S" => Some(Small)
   | "M" => Some(Medium)
   | "L" => Some(Large)
   | "XL" => Some(XLarge(1))
   | "XXL" => Some(XLarge(2))
   | "XXXL" => Some(XLarge(3))
   | "XXXXL" => Some(XLarge(4))
   | _ => None
  };
};

let getValue = (element: option(Elem.t)): option(string) => {
  element 
  -> Belt.Option.map(Elem.unsafeAsHtmlElement)
  -> Belt.Option.map(D.HtmlElement.value);
};

let toInt = (s:string): option(int) => {
  switch (int_of_string(s)) {
    | result => Some(result)
    | exception(Failure(_)) => None
  }
};


let calculate =(_ : Dom.event) : unit => {
  let quantity = getValue(Doc.getElementById(D.document, "quantity"))
    -> Belt.Option.flatMap(_, toInt);

  let unitPrice = getValue(Doc.getElementById(D.document, "size"))
    -> Belt.Option.flatMap(shirtSizeOfString)
    -> price;

  let totalPrice = switch(unitPrice, quantity) {
    | (Some(uPrice), Some(qty)) => Some(uPrice *. float_of_int(qty))
    | (_, _) => None
  };

  let priceString = switch(totalPrice) {
    | Some(total) => Js.Float.toFixedWithPrecision(total, ~digits=2)
    | None => ""
  };

  let _ = Doc.getElementById(D.document, "price")
    -> Belt.Option.map(_, Elem.setInnerText(_, priceString));

  (); /* return unit */
};

/*
// Not needed anymore because of the event handling for quantity and size
let calcButton = Doc.getElementById(D.document, "calculate");
switch (calcButton) {
  | Some(element) =>
      Js.log("HTML element 'calculate' found");
      D.EventTarget.addEventListener(
        Elem.asEventTarget(element), "click", calculate)
  | None => 
     Js.log("HTML element 'calculate' not found");
     ()
};
*/

let quantityInput = Doc.getElementById(D.document, "quantity");
switch (quantityInput) {
  | Some(element) =>
      Js.log("HTML element 'quantity' found");
      D.EventTarget.addEventListener(
        Elem.asEventTarget(element), "input", calculate)
  | None =>
      Js.log("HTML element 'quantity' not found");
      ()
};

let sizeSelect = Doc.getElementById(D.document, "size");
switch (sizeSelect) {
  | Some(element) =>
      Js.log("HTML element 'size' found");
      D.EventTarget.addEventListener(
        Elem.asEventTarget(element), "change", calculate)
  | None =>
     Js.log("HTML element 'size' not found");
     ()
};
