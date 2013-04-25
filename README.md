kajiiiro_rest_server
====================

【概要】

rest webサーバ
観点はすぐに使えて簡単に試せること。
いつも感じることだが、
とにかくwebアプリケーションを試したいのに、
設定ファイルを変える(それなりに内容も理解して)必要があったり、
http methodを許可したり、
c++用のwebサーバがなかったり…

もう色々面倒い！

だから作った！

・フルスクラッチのc++webサーバ

・学習用であり、ライブラリ非依存(pthreadには依存)

・RESTfulに対応

・とりあえずchromeからアクセスできる

【使い方】

<pre>
int main()
{
        // port 7766で起動する例
        kajiiiro::Server server;
        server.setListener(new kajiiiro::SampleRestListener());
        if (false == server.start())
                return 1;
        return 0;
}
</pre>

ホスト:7766/testにブラウザでアクセスする。
その他、APIはヘッダファイルをみること。かなりわかりやすく書いたつもり。

【課題】

・スレッドによる複数アクセス未対応

【クラス構成】

・Uri
        URIの操作を行うクラス

・Request
        リクエスト情報を操作するクラス

・Response
        レスポンス情報を操作するクラス

・Listener
        実際の処理を行うクラス。Request, Responseを受け取りレスポンスを作成する。
        get等の4つのメソッド用関数を定義する

・Session
        ソケット情報を保持するクラス
        送信処理、受信処理も受け持つ。また、Listener内部でクライアントとの切断にも答える

・Server
        ソケットの切断タイミング、スレッド管理を行うクラス

・Helper
        各種分類しづらいものすべてを任せる便利クラス
        httpは文字列操作が多いので、それを行おうかと考え中

