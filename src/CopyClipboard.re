/* src/CopyClipboard.re */

[@bs.module "react-copy-to-clipboard"] [@react.component]
external make: (~title: string, ~children: React.element) => React.element =
  "CopyToClipboard";
