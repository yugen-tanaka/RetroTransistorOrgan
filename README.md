# RetroTransistorOrgan

![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![Platform: macOS / iOS](https://img.shields.io/badge/Platform-macOS%20%7C%20iOS-lightgrey.svg)
![Format: AUv3 Instrument](https://img.shields.io/badge/Format-AUv3%20Plugin-orange.svg)

1970年代のレトロな電子オルガン（アナログトランジスタオルガン）から着想を得て開発した、**AUv3（Audio Unit v3）インストゥルメントプラグイン** です。


---

## ✨ 主な機能 (Features)

- **AUv3 プラグイン対応**: Logic Pro, GarageBand などのホストアプリ / DAW でプラグインとして読み込める。
- **2段鍵盤 + ペダル鍵盤のシミュレーション**:
  - **Upper（上段鍵盤）**: Tibia (16', 8', 4', 2 2/3'), String (16', 8', 4'), Diapason 8', Clarinet 8', Oboe 8'
  - **Lower（下段鍵盤）**: Tibia (8', 4'), Diapason 8', String (8', 4'), Horn 8'
  - **Pedal（足踏みペダル）**: Bourdon 16', Major Flute 8'（サステイン時間調整機能付き）
- **内蔵エフェクト**:
  - ビブラート（Vibrato）
  - アンサンブル（Ensemble）: ONにした時、Stationary系統の信号がRotor系統にミックスされ、Stationary系統の信号はオフになります。Stationary系統の信号にもレスリー効果をかけたい場合にオンにします。
- **リアルタイムC++ DSPエンジン**: 矩形波・階段波オシレーター、マルチモード・フィルタによるアナログ風音合成。トップオクターブ発振+分周方式に特徴的な全鍵の位相同期を再現。
- **レトロ風コントロールパネル**: カワイ電子オルガンKE-310の実機をモデルにして、タブレット・トーンレバーやノブ風UIをSwiftUIで再現。

---

## 💻 動作環境 (Requirements)

- **OS**: macOS 15.0 以降 / iOS 18.0 以降
- **開発環境**: Xcode 16.0 以降
- **対応言語**: Swift / C++ (Swift/C++ Interoperability)
- **対応ホスト**: AUv3（aumu）プラグイン規格に対応したDAW / ホストアプリ （スタンドアローンでは音が出ません）

---

## 🛠 ビルドおよび実行手順 (Build & Run)

1. リポジトリをクローンします。
   ```bash
   git clone https://github.com/yugen-tanaka/RetroTransistorOrgan.git
   cd RetroTransistorOrgan
   ```
2. `RetroTransistorOrgan.xcodeproj` を Xcode で開きます。
3. ターゲットとして `RetroTransistorOrganExtension` を選択します。
4. 自身の Apple ID / 開発者アカウントで Code Signing を設定します。
5. `Cmd + R` でビルド・実行します。


## テンプレート
リリースのzipファイルには、Logic Proのプロジェクトを同梱しています。本プラグインから出力された音声のルーティングや、レスリーやスプリングリバーブなどのオーディオエフェクトプラグインが設定されています。もちろんテンプレートを使わなくてもプラグインをご使用いただけます。

## ⚠️ 免責事項 (Disclaimer)

本プロジェクトは **実験的・学習目的のオープンソースプロジェクト** です。
個人の趣味・研究開発として作成されたものであり、プロフェッショナルな音楽制作環境での動作保証や個別の技術サポートは行っておりません。あらかじめご了承ください。

---

## 📄 ライセンス (License)

このプロジェクトは [MIT License](LICENSE) のもとで公開されています。商用・非商用を問わず自由にご利用・改変いただけます。
