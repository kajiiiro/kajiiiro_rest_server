--本システムが用いるDB構成sql

--テーブル削除sql一覧
--DROP TABLE configure ;

--テーブル作成sql一覧
CREATE TABLE configure (
    no serial
    , item text primary key
    , string_value text         -- value is int, this is null
    , integer_value integer     -- value is string, this is null
    , valid boolean not null
) ;

--デフォルト設定の挿入
INSERT INTO configure VALUES (default, 'server_port', null, 7766, true);


--リソーステーブル作成
--client_id + uri_nameが提供するリソース名称とする
CREATE TABLE resource (
    client_id serial
    , uri_name text
    , create_time timestamp not null
    , access_time timestamp not null
    , primary key
    (
        client_id
        , uri_name
    )
);
