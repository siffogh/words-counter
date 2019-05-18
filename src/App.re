[%bs.raw {|require('./App.css')|}];

[@react.component]
let make = () => {
  let (text, setText) = React.useState(() => "");

  let handleTextChange = e => ReactEvent.Form.target(e)##value |> setText;

  let handleClearClick = _ => setText(_ => "");

  let wordsCountText =
    (text |> Utils.countWordsInString |> string_of_int) ++ " words";

  <div className="App">
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