[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  let page =
    switch (url.path) {
    | [] => <Home />
    | ["login"] => <Login />
    | _ => <div> {"Page not found :/" |> ReasonReact.string} </div>
    };

  <div className="App"> page </div>;
};