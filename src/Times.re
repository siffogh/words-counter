/* src/Times.re */

[@bs.module "./times.svg"] [@react.component]
external make: (~height: string) => React.element = "default";