exception PostError(string);

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
         switch (Js.Json.decodeObject(response)) {
         | Some(decodedRes) =>
           switch (Js.Dict.get(decodedRes, "error")) {
           | Some(error) =>
             switch (Js.Json.decodeObject(error)) {
             | Some(decodedErr) =>
               switch (Js.Dict.get(decodedErr, "message")) {
               | Some(errorMessage) =>
                 switch (Js.Json.decodeString(errorMessage)) {
                 | Some(decodedErrorMessage) =>
                   reject(PostError(decodedErrorMessage))
                 | None => reject(PostError("POST_ERROR"))
                 }
               | None => resolve(decodedRes)
               }
             | None => resolve(decodedRes)
             }

           | None => resolve(decodedRes)
           }
         | None => resolve(Js.Dict.empty())
         }
       )
  );
};