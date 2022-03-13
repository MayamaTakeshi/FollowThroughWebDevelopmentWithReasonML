
let orderList = [(7, ShirtSize.Medium), 
                 (5, ShirtSize.XLarge(3)),
                 (4, ShirtSize.Small),
                 (6, ShirtSize.Large),
                 (8, ShirtSize.Small),
                 (2, ShirtSize.Large),
                 (9, ShirtSize.Medium),
                 (3, ShirtSize.XLarge(2))];

let onePrice = ((qty: int, size: ShirtSize.t)) : float => {
 float_of_int(qty) *. ShirtSize.price(size);
};

let priceList = Belt.List.map(orderList, onePrice);

let isMedium = ((_, size)) : bool => {
  size == ShirtSize.Medium;
};

let mediums = Belt.List.keep(orderList, isMedium);

let mediums2 = Belt.List.keep(orderList, ((_, size)) => size == ShirtSize.Medium);

let addPriceLogged = (runningTotal,orderItem) => {
 let price = onePrice(orderItem);
 Js.log({j|$runningTotal, $price|j});
 runningTotal +. price;
};

Js.log("Running total / Price");
let totalPrice = Belt.List.reduce(orderList, 0.0, addPriceLogged);
Js.log2("Total price:", totalPrice);

let addPriceToTotal = (runningTotal, price) => runningTotal +. price;

let totalPrice2 =
 Belt.List.map(orderList, onePrice) ->
 Belt.List.reduce(_, 0.0, addPriceToTotal);
Js.log2("Total price:", totalPrice2);

let totalPrice3 = 
 Belt.List.map(orderList, onePrice) ->
 Belt.List.reduce(_, 0.0, (+.));
Js.log2("Total price:", totalPrice3);

let mediumTotal = 
  Belt.List.keep(orderList, isMedium) ->
  Belt.List.map(onePrice) ->
  Belt.List.reduce(0.0, (+.));
Js.log2("mediumTotal:", mediumTotal);
