exception PostError(string);

[@decco]
type error = {message: string};

[@decco]
type response = {error: option(error)};

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
    |> then_(response =>
         switch (response_decode(response)) {
         | Belt.Result.Ok({error: Some({message})}) =>
           reject(PostError(message))
         | response => resolve(response)
         }
       )
  );
};