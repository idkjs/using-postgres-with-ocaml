open Opium;

let (let.bind) = Lwt.bind;

/* GET /messages */
let read_all_messages =
  App.get("/messages", _request => {
    let.bind messages = Storage.read_all_messages();
    let json = [%to_yojson: list(Storage.message)](messages);
    Lwt.return(Response.of_json(json));
  });

/* POST /messages */
let post_message =
  App.post("/messages", request => {
    let.bind input_json = Request.to_json_exn(request);
    let input_message =
      switch (Storage.message_of_yojson(input_json)) {
      | Ok(message) => message
      | Error(error) => raise(Invalid_argument(error))
      };

    let.bind () = Storage.insert_message(input_message);
    Lwt.return(Response.make(~status=`OK, ()));
  });

let () = App.empty |> read_all_messages |> post_message |> App.run_multicore;
