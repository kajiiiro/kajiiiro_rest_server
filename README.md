kajiiiro_rest_server
====================

【概要】

rest webサーバ
観点はすぐに使えて簡単に試せること。
いつも感じることだが、
とにかくwebを試したいのに設定ファイルを変えたり、
webアプリを作りたいのに色々準備したり、
c++用のwebサーバがなかったり…
もう色々面倒い！

だから作りました！

・フルスクラッチのc++webサーバ

・学習用であり、ライブラリ非依存

・RESTfulに対応

・とりあえずchromeからアクセスできる

【使い方】

// port 7766で起動します

kajiiiro::Server server;

server.setListener(new kajiiiro::SampleRestListener());

server.start();

ホスト:7766にブラウザでアクセスしてみてください。
その他、APIはヘッダファイルをみること。簡単です。

【課題】

・REST未対応
・スレッドによる複数アクセス未対応

【クラス構成】

・Uri        URIの操作を行うクラス

・Request    リクエスト情報を操作するクラス

・Response   レスポンス情報を操作するクラス

・Listener   実際の処理を行うクラス。Request, Responseを受け取りレスポンスを作成する。

・Session    ソケット情報を保持するクラス
        送信処理、受信処理も受け持つ。また、Listener内部でクライアントとの切断にも答える。

・Server     ソケットの切断タイミング、スレッド管理を行うクラス

・Helper     各種分類しづらいものすべてを任せる便利クラス
        httpは文字列操作が多いので、それを行おうかと考え中

