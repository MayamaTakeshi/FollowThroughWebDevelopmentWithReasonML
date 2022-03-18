let component = ReasonReact.statelessComponent(__MODULE__);

let handleClick = (_event, _self) => Js.log("clicked!");

let make = (~message, ~children) => {
  ...component,

  render: self =>
   <div onClick=(self.handle(handleClick))>
    {ReasonReact.string(message)}
  </div>,
};


