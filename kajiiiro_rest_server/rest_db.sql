--本システムが用いるDB構成sql

--テーブル削除sql一覧
--DROP TABLE configure ;

--テーブル作成sql一覧
CREATE TABLE configure (no serial, item text, string_value text, integer_value integer, valid boolean) ;

--デフォルト設定の挿入
INSERT INTO configure VALUES (default, 'server_port', null, 7766, true);
