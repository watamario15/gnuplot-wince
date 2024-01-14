# Gnuplot 4.4.3 for Windows CE Rev. 2

![](image.png)

This is a *Windows CE only partial* port of Gnuplot 4.4.3. This port is as destructive as dropping support for environments except for Windows Mobile 5.0 Pocket PC SDK on Visual Studio 2005/2008, and implementing only basic features. This is a slight update to the version made by [skawamoto0](https://github.com/skawamoto0) distributed [here](https://kawamoto.no-ip.org/henteko/myapp/gplotwce4431.zip), incorporating some fixes and small improvements.

## How To Run

Download from [Releases](../../releases), extract it into a ASCII-only path (the top folder is recommended), and run `wgnuplot.exe` on your device.

The console screen expects "MS Gothic" font to be available. While this app should run without it, you might face some issues in that case.

`wgnuplot.ini` is not supported.

The charset recognized for this software is UTF-8, thus write `.plt` file in UTF-8. You can use non-ASCII characters on the console although they don't show up while on console.

You must set a font with required glyphs with commands like `set title font` to correctly render a graph contains non-ASCII characters.

## How To Build

Use the `.sln` file located in `vs2005`/`vs2008` on Visual Studio 2005/2008. "Smart Device Programability" and [Windows Mobile 5.0 Pocket PC SDK](https://www.microsoft.com/en-us/download/details.aspx?id=42) must be installed to build this project.

## License

My ([watamario15](https://github.com/watamario15)'s) modifications are provided as public domain. If you want more formal license, I will license my modifications under the terms of the [CC0-1.0](https://creativecommons.org/publicdomain/zero/1.0/) license.

However, this work is just a modification of another piece of software. Carefully read original documents (especially [Copyright](Copyright)) and [skawamoto0's readme](readme-kawamoto.txt) before using this software.

My contact information can be obtained by invoking the `git log` command within the Git repository.

----

# Gnuplot 4.4.3 for Windows CE Rev 2

![](image-ja.png)

これは **Windows CE 専用で部分的な** Gnuplot 4.4.3 の移植版です。破壊的な移植なので、Visual Studio 2005/2008 上の Windows Mobile 5.0 Pocket PC SDK のみに対応し、実装されている機能も最低限です。[skawamoto0](https://github.com/skawamoto0) 氏が[こちら](https://kawamoto.no-ip.org/henteko/myapp/gplotwce4431.zip)で公開されているものに対し、修正や少しの改良を施した版となります。

## 実行方法

[Releases](../../releases) からダウンロード・展開し、日本語などの非 ASCII 文字を含まない場所（最上層を推奨）に配置します。その後、`wgnuplot.exe` を直接起動します。日本語を含むパスに配置できない制約から「アプリ」フォルダに配置できないので、辞書アプリからの起動には対応しません。Explorer や ceOpener などを用いてください。

コンソール画面には「MS Gothic」フォントを用いるように指定しているので、このフォントを導入した環境での利用を推奨します。

日本語化済みの環境では、元の `wgnuplot.mnu` を削除・移動・改名などした上で `wgnuplot-ja.mnu` を `wgnuplot.mnu` に改名することで、メニューを日本語表示にできます。

`wgnuplot.ini` の読み込みには対応しません。

このソフトウェアは UTF-8 でファイルの入出力を行います。そのため、`.plt` ファイルは UTF-8 で作成してください。コンソール画面での直接入力でも日本語等を使用できますが、コンソール上では ASCII 文字のみが表示されます。

グラフにおいて日本語などの非 ASCII 文字を表示する場合は、`set title font` コマンドなどを用いて必要なグリフを持つフォントを指定する必要があります。

## ビルド方法

Visual Studio 2005/2008 を用いて `vs2005`/`vs2008` フォルダ内の `.sln` ファイルを開き、ビルドします。「スマート デバイス プログラマビリティ」と [Windows Mobile 5.0 Pocket PC SDK](https://www.microsoft.com/en-us/download/details.aspx?id=42) が必須です。

## ライセンス

私（[watamario15](https://github.com/watamario15)）の変更分に関しては public domain とします。より正式なライセンスが必要な場合は [CC0-1.0](https://creativecommons.org/publicdomain/zero/1.0/) でライセンスします。

ただし、本ソフトウェアはあくまでも既存ソフトウェアへの修正に過ぎないことに注意し、元の Gnuplot の文書（特に [Copyright](Copyright)）や [skawamoto0 氏の readme](readme-kawamoto.txt) を必ず確認してください。

私への連絡先は、Git リポジトリ内で `git log` コマンドを打つことで取得できます。
