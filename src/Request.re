exception PostError(string);

type error = {message: string};
type response = {
  error: option(error),
  idToken: string,
};

module Decode = {
  let error = json =>
    Json.Decode.{message: json |> field("message", string)};

  let response = json =>
    Json.Decode.{
      error: json |> field("error", optional(error)),
      idToken: json |> field("idToken", string),
    };
};

let post = (url, payload) => {
  let stringifiedPayload = payload |> Js.Json.object_ |> Js.Json.stringify;

  Js.Promise.(
    Fetch.fetchWithInit(
      url,
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(stringifiedPayload),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => {
         let response = Decode.response(json);
         switch (response.error) {
         | Some(err) => reject(PostError(err.message))
         | None => resolve(response)
         };
       })
  );
};