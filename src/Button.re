[%bs.raw {|require('./Button.css')|}];

type categoryT =
  | SECONDARY
  | PRIMARY;

let classNameOfCategory = category =>
  "Button "
  ++ (
    switch (category) {
    | SECONDARY => "secondary"
    | PRIMARY => "primary"
    }
  );

[@react.component]
let make =
    (
      ~onClick,
      ~title: string,
      ~children: ReasonReact.reactElement,
      ~disabled=false,
      ~category=SECONDARY,
    ) => {
  <button onClick className={category |> classNameOfCategory} title disabled>
    children
  </button>;
};