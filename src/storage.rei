[@deriving yojson]
type message = {
  user_name: string,
  body: string,
};

exception Query_failed(string);

let read_all_messages: unit => Lwt.t(list(message));

let insert_message: message => Lwt.t(unit);
