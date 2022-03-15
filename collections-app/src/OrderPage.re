let commaSplit = (s: string) : array(string) => {
 let pattern = [%re "/\\s*,\\s*/"];
 Js.String.splitByRe(pattern, s) ->
  Belt.Array.map(_, (item) => {
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
