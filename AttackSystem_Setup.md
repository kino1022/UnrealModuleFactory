# AnimNotifyを使用した攻撃判定システムの実装ガイド

## 概要

AnimationMontageの特定区間で攻撃判定を出すシステムを実装しました。このシステムは以下のコンポーネントで構成されています：

## 実装されたファイル

### 1. **AnimNotifyState_AttackWindow**
- `Public/Animation/AnimNotifyState_AttackWindow.h`
- `Private/Animation/AnimNotifyState_AttackWindow.cpp`

AnimationMontageのタイムライン上に配置し、攻撃判定の有効区間を定義します。

**主要プロパティ：**
- `AttackTypeTag`: 攻撃の種類を識別するGameplayTag
- `bContinuousDetection`: 毎フレーム判定を実行するか（連続ヒット可能）
- `bDrawDebug`: デバッグ用の判定範囲可視化

### 2. **AttackHitInterface**
- `Public/Animation/AttackHitInterface.h`

AnimNotifyとGameplayAbility間の通信インターフェースです。

**主要メソッド：**
- `OnAttackWindowBegin`: 攻撃判定開始時
- `ExecuteAttackHitDetection`: 攻撃判定実行
- `OnAttackWindowEnd`: 攻撃判定終了時

### 3. **SimpleAttackActionAbility（拡張）**
- `Public/Action/SimpleAttackActionAbility.h`
- `Private/Action/SimpleAttackActionAbility.cpp`

実際の攻撃判定ロジックを実装したGameplayAbilityです。

**主要プロパティ：**
- `AttackMontage`: 再生する攻撃モンタージュ
- `TraceShape`: 攻撃判定の形状（Sphere/Box/Capsule）
- `TraceExtent`: 判定範囲のサイズ
- `TraceStartOffset`: 判定開始位置（キャラクター相対）
- `TraceEndOffset`: 判定終了位置（キャラクター相対）
- `DamageEffectClass`: ヒット時に適用するGameplayEffect
- `TraceChannel`: 攻撃対象のコリジョンチャンネル

### 4. **CharacterBase（拡張）**
- `Public/Character/CharacterBase.h`
- `Private/Character/CharacterBase.cpp`

`IAttackHitInterface`を実装し、AnimNotifyからの呼び出しをAbilityに転送します。

## セットアップ手順

### ステップ1: AnimationMontageの設定

1. 攻撃用のAnimationMontageを開く
2. タイムライン上の攻撃判定を出したい区間を選択
3. **右クリック → Add Notify State → Attack Window**を追加
4. AnimNotifyStateのプロパティを設定：
   - `AttackTypeTag`: 任意のGameplayTag（例: `Ability.Attack.Light`）
   - `bContinuousDetection`: 連続ヒット判定が必要ならtrue
   - `bDrawDebug`: テスト時はtrueにして判定範囲を可視化

### ステップ2: SimpleAttackActionAbilityの設定

1. Content Browserで**SimpleAttackActionAbility**のBlueprintを作成
2. 以下のプロパティを設定：

```
Attack | Animation:
  - AttackMontage: 作成した攻撃モンタージュを指定

Attack | Detection:
  - TraceShape: Sphere/Box/Capsuleから選択
  - TraceExtent: 
    * Sphere: X値が半径（例: 50.0）
    * Box: XYZが半サイズ（例: 50, 50, 50）
    * Capsule: Xが半径、Zが半分の高さ（例: 30, 0, 60）
  - TraceStartOffset: 攻撃開始位置（例: 0, 0, 0）
  - TraceEndOffset: 攻撃終了位置（例: 100, 0, 50）
  - TraceChannel: ECC_Pawn（または任意のチャンネル）

Attack | Damage:
  - DamageEffectClass: ダメージ用GameplayEffectを指定
```

### ステップ3: GameplayEffectの作成

1. ダメージ用のGameplayEffectを作成（例: `GE_MeleeDamage`）
2. DurationType: Instant
3. Modifiersを追加：
   - Attribute: Health（または体力アトリビュート）
   - Operation: Add
   - Magnitude: -10.0（ダメージ量）

### ステップ4: AbilitySystemへの登録

1. CharacterのAbilitySetまたはAbilityInputConfigに追加
2. 入力アクションとバインド（例: 左クリック、攻撃ボタン）

## 使用例

### 基本的な使い方

```cpp
// CharacterBaseに自動で実装済み
// AnimNotifyState_AttackWindowを配置するだけで動作します
```

### カスタマイズ例

複数の攻撃タイプを作る場合：

1. 各攻撃用のAbilityを作成（例: `GA_LightAttack`, `GA_HeavyAttack`）
2. それぞれに異なるモンタージュと判定設定を適用
3. AnimNotifyStateの`AttackTypeTag`で区別

## デバッグ方法

1. AnimNotifyStateの`bDrawDebug`をtrueに設定
2. ゲームを実行して攻撃を使用
3. 画面上に判定範囲が可視化される：
   - **緑の図形**: 判定開始位置
   - **赤の図形**: 判定終了位置
   - **オレンジの球**: ヒット箇所

## トラブルシューティング

### 攻撃判定が出ない場合

1. CharacterがAbilitySystemComponentを持っているか確認
2. Abilityが正しくGrantされているか確認
3. AnimMontageにAnimNotifyState_AttackWindowが配置されているか確認
4. `bDrawDebug`をtrueにして判定範囲を確認

### ヒットしても何も起きない場合

1. ターゲットがAbilitySystemComponentを持っているか確認
2. DamageEffectClassが正しく設定されているか確認
3. TraceChannelが対象のコリジョン設定と一致しているか確認

### 連続でヒットしすぎる場合

1. AnimNotifyStateの`bContinuousDetection`をfalseに設定
2. 攻撃判定の区間（NotifyStateの長さ）を短くする

## 拡張のヒント

### ソケットベースの攻撃判定（別実装）

武器や腕の動きに沿った判定が必要な場合は、**SocketBasedAttackActionAbility**を使用してください。

詳細は [SocketBasedAttack_Setup.md](./SocketBasedAttack_Setup.md) を参照。

**使い分け:**
- **SimpleAttack**: シンプルな固定範囲攻撃、パンチ・キックなど
- **SocketBasedAttack**: 武器の軌跡追従、剣・槍などの攻撃

### コンボシステムへの拡張

```cpp
// SimpleAttackActionAbilityを継承して
// コンボカウンターやコンボウィンドウを追加
```

### 武器別の判定範囲

```cpp
// Characterに装備中の武器情報を持たせて
// PerformAttackTrace内でTraceExtentを動的に変更
```

### ヒットストップ・ヒットエフェクト

```cpp
// PerformAttackTrace内のヒット処理部分に追加
// - タイムディレーション
// - パーティクル再生
// - サウンド再生
```

## システムの仕組み

```
1. プレイヤーが攻撃入力
   ↓
2. SimpleAttackActionAbility::ActivateAbility
   ↓
3. AnimationMontage再生開始
   ↓
4. AnimNotifyState_AttackWindow::NotifyBegin
   ↓
5. IAttackHitInterface::OnAttackWindowBegin
   ↓
6. SimpleAttackActionAbility::bIsAttackWindowActive = true
   ↓
7. AnimNotifyState_AttackWindow::NotifyTick（毎フレーム）
   ↓
8. IAttackHitInterface::ExecuteAttackHitDetection
   ↓
9. SimpleAttackActionAbility::PerformAttackTrace
   - コリジョン判定実行
   - ヒットしたアクターにGameplayEffectを適用
   ↓
10. AnimNotifyState_AttackWindow::NotifyEnd
   ↓
11. SimpleAttackActionAbility::bIsAttackWindowActive = false
```

## まとめ

このシステムにより：
- ✅ アニメーションと完全に同期した攻撃判定
- ✅ デザイナーがエディタ上で調整可能
- ✅ 複数の攻撃タイプに対応
- ✅ デバッグ機能完備
- ✅ GASとの完全統合

が実現できました。

