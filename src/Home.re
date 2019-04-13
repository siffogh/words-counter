[%bs.raw {|require('./Home.css')|}];

let countWordsInString = text => {
  let spacesRegex = Js.Re.fromString("\s+");

  switch (text) {
  | "" => 0
  | noneEmptyText =>
    noneEmptyText
    |> Js.String.trim
    |> Js.String.splitByRe(spacesRegex)
    |> Js.Array.length
  };
};

module Times = {
  [@bs.module "./icons/times.svg"] [@react.component]
  external make: (~height: string) => React.element = "default";
};

module Copy = {
  [@bs.module "./icons/copy.svg"] [@react.component]
  external make: (~height: string) => React.element = "default";
};

module CopyClipboard = {
  [@bs.module "react-copy-to-clipboard"] [@react.component]
  external make: (~text: string, ~children: React.element) => React.element =
    "CopyToClipboard";
};

[@react.component]
let make = () => {
  let (text, setText) = React.useState(() => "");

  let handleTextChange = e => ReactEvent.Form.target(e)##value |> setText;

  let handleClearClick = _ => setText(_ => "");

  let wordsCountText =
    (text |> countWordsInString |> string_of_int) ++ " words";

  <div className="Home">
    <div className="header">
      <h3> {"Words Counter" |> ReasonReact.string} </h3>
      <span> {ReasonReact.string(wordsCountText)} </span>
    </div>
    <textarea
      placeholder="Express yourself..."
      value=text
      onChange=handleTextChange
    />
    <div className="footer">
      <Button
        title="Clear text"
        onClick=handleClearClick
        disabled={String.length(text) === 0}>
        <Times height="20px" />
      </Button>
      <CopyClipboard text>
        <Button
          title="Copy text"
          disabled={String.length(text) === 0}
          category=Button.PRIMARY>
          <Copy height="20px" />
        </Button>
      </CopyClipboard>
    </div>
  </div>;
};