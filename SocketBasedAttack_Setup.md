# SocketBasedAttackActionAbility - ソケットベース攻撃判定システム

## 概要

`SocketBasedAttackActionAbility`は、武器や腕のソケット位置に追従した攻撃判定を実現する新しいActionAbilityです。アニメーションの動きに沿って正確な判定を出すことができます。

## 特徴

### 🎯 主要機能

✅ **ソケット追従**: 武器や手のソケットに判定が追従
✅ **連続トレース**: 前フレームから現フレームへの軌跡を判定
✅ **高速振りに対応**: 速い攻撃でも判定抜けしにくい
✅ **柔軟な設定**: 2つのソケット間でトレース可能
✅ **デバッグ機能**: ソケット位置とトレース軌跡を可視化

### SimpleAttackActionAbilityとの違い

| 項目 | SimpleAttack | SocketBasedAttack |
|------|--------------|-------------------|
| 判定基準 | キャラクター固定位置 | ソケット位置 |
| アニメーション追従 | × | ✅ |
| 武器の軌跡追従 | × | ✅ |
| 判定形状 | Sphere/Box/Capsule | Sphere（軌跡） |
| 用途 | シンプルな攻撃 | 武器振り、複雑な攻撃 |

## 実装ファイル

- **ヘッダー**: `Source/UnrealModuleFactory/Public/Action/SocketBasedAttackActionAbility.h`
- **実装**: `Source/UnrealModuleFactory/Private/Action/SocketBasedAttackActionAbility.cpp`

## セットアップ手順

### ステップ1: ソケットの準備

1. キャラクターのSkeletalMeshを開く
2. 必要なソケットを追加：
   - 例: `hand_r` (右手)
   - 例: `weapon_start` (武器の根本)
   - 例: `weapon_tip` (武器の先端)

### ステップ2: Abilityの作成

1. Content Browserで右クリック → Blueprint Class
2. Parent Classで **SocketBasedAttackActionAbility** を選択
3. 名前を設定（例: `GA_SwordSlash`）

### ステップ3: プロパティの設定

Abilityを開いて以下のプロパティを設定：

```
Attack | Animation:
  - AttackMontage: 攻撃モンタージュを指定

Attack | Socket:
  - TraceStartSocketName: "hand_r" または "weapon_start"
  - TraceEndSocketName: "weapon_tip" または "hand_l"
  - StartSocketOffset: (0, 0, 0) ※微調整用
  - EndSocketOffset: (0, 0, 0) ※微調整用

Attack | Detection:
  - TraceRadius: 30.0 ※判定の半径（cm）
  - TraceChannel: ECC_Pawn

Attack | Damage:
  - DamageEffectClass: ダメージ用GameplayEffectを指定
```

### ステップ4: AnimationMontageの設定

1. 攻撃モンタージュを開く
2. 攻撃判定を出したい区間に **AnimNotifyState_AttackWindow** を配置
3. プロパティを設定：
   - `bContinuousDetection`: **true**（推奨）
   - `bDrawDebug`: テスト時はtrue

### ステップ5: AbilitySystemへの登録

通常のAbilityと同じく、AbilitySetやAbilityInputConfigに登録

## 使用例

### 基本的な剣の振り

```
TraceStartSocketName: "weapon_start"
TraceEndSocketName: "weapon_tip"
TraceRadius: 30.0
bContinuousDetection: true
```

これで、剣の根本から先端までの軌跡全体が判定範囲になります。

### 素手での攻撃

```
TraceStartSocketName: "hand_r"
TraceEndSocketName: "hand_r"
EndSocketOffset: (50, 0, 0)  // 手から前方50cm
TraceRadius: 20.0
```

手の位置から前方にオフセットした位置までトレースします。

### 両手を使った攻撃

```
TraceStartSocketName: "hand_r"
TraceEndSocketName: "hand_l"
TraceRadius: 40.0
```

右手から左手の間をトレースします（両手叩きつけなど）。

## 連続トレースの仕組み

```
フレーム1: 武器位置 A
            ↓
フレーム2: 武器位置 B → A から B までトレース
            ↓
フレーム3: 武器位置 C → B から C までトレース
```

この仕組みにより、**高速な武器の振りでも判定抜けが発生しにくく**なります。

## デバッグ方法

`bDrawDebug = true`で以下が可視化されます：

- **黄色の線**: トレースの軌跡
- **緑の球**: トレース開始位置
- **赤の球**: トレース終了位置
- **水色の小球**: ソケットの実際の位置
- **オレンジの球**: ヒット箇所
- **白い線**: ヒット法線

## よくある設定例

### 1. 大剣の薙ぎ払い

```cpp
TraceStartSocketName: "weapon_root"
TraceEndSocketName: "weapon_tip"
TraceRadius: 50.0  // 大きめの判定
bContinuousDetection: true
```

### 2. 短剣の突き

```cpp
TraceStartSocketName: "hand_r"
TraceEndSocketName: "dagger_tip"
TraceRadius: 15.0  // 小さめの判定
bContinuousDetection: true
```

### 3. パンチ・キック

```cpp
// パンチ
TraceStartSocketName: "hand_r"
TraceEndSocketName: "hand_r"
EndSocketOffset: (30, 0, 0)
TraceRadius: 20.0

// キック
TraceStartSocketName: "foot_r"
TraceEndSocketName: "foot_r"
EndSocketOffset: (40, 0, 0)
TraceRadius: 25.0
```

### 4. 槍の突進攻撃

```cpp
TraceStartSocketName: "spear_shaft"
TraceEndSocketName: "spear_tip"
TraceRadius: 20.0
bContinuousDetection: true
```

## トラブルシューティング

### ソケットが見つからないエラー

```
SocketBasedAttackActionAbility: Socket 'weapon_tip' does not exist!
```

**解決方法:**
1. SkeletalMeshにソケットが正しく追加されているか確認
2. ソケット名のスペルミスをチェック
3. 大文字小文字が一致しているか確認

### 判定が出ない

1. `bContinuousDetection`をtrueにしているか確認
2. AnimNotifyStateが正しい区間に配置されているか確認
3. `bDrawDebug = true`でトレースが実行されているか確認

### 判定がずれる

1. `bDrawDebug = true`でソケット位置を確認
2. `StartSocketOffset`や`EndSocketOffset`で微調整
3. ソケットの位置をSkeletalMesh上で調整

### 判定が抜ける

1. `TraceRadius`を大きくする
2. `bContinuousDetection = true`になっているか確認
3. アニメーションのフレームレートが低すぎないか確認

## 高度な使い方

### 複数の攻撃判定

同じモンタージュ内に複数のAnimNotifyState_AttackWindowを配置して、段階的な判定を実現：

```
前半: 柄当て（TraceStartSocketName: "weapon_root"）
後半: 刃先当て（TraceStartSocketName: "weapon_tip"）
```

### 攻撃タイプごとの判定

同じAbilityで、AnimNotifyStateの`AttackTypeTag`によって異なる処理：

```cpp
// PerformAttackTrace内でAttackTypeTagをチェック
if (AttackTypeTag.MatchesTag(FGameplayTag::RequestGameplayTag("Attack.Heavy")))
{
    // 重攻撃用の処理
}
```

### 武器の持ち替え対応

キャラクターの装備状態に応じてソケット名を切り替え：

```cpp
// Blueprintで装備に応じてAbilityのプロパティを変更
if (EquippedWeapon == Sword)
{
    Ability->TraceEndSocketName = "sword_tip";
}
else if (EquippedWeapon == Axe)
{
    Ability->TraceEndSocketName = "axe_blade";
}
```

## パフォーマンス考慮事項

### 最適化のヒント

1. **TraceRadiusは必要最小限に**: 大きすぎる判定は負荷増
2. **同時発動する攻撃数を制限**: 多数の敵が同時攻撃すると重い
3. **TraceChannelを限定**: 不要なオブジェクトは無視設定

### 推奨設定

```
通常攻撃: TraceRadius 20-40
重攻撃: TraceRadius 40-60
範囲攻撃: TraceRadius 60-100
```

## SimpleAttackとの使い分け

### SimpleAttackActionAbilityを使う場合

- シンプルな攻撃（パンチ、キックなど）
- 固定範囲の攻撃
- ボックス型やカプセル型の判定が必要
- パフォーマンス重視

### SocketBasedAttackActionAbilityを使う場合

- 武器を使った攻撃
- 複雑な軌道の攻撃
- 正確な判定が必要
- 武器の長さや動きが重要

## まとめ

SocketBasedAttackActionAbilityにより：

✅ 武器の振りに沿った正確な判定
✅ 高速な攻撃でも判定抜けしにくい
✅ アニメーションと完全同期
✅ 柔軟なソケット設定
✅ 既存のAnimNotifyシステムと互換

が実現できました！

---

## 関連ドキュメント

- [AttackSystem_Setup.md](./AttackSystem_Setup.md) - 基本的な攻撃システムのセットアップ
- SimpleAttackActionAbility - 固定位置ベースの攻撃判定
- AnimNotifyState_AttackWindow - 攻撃判定ウィンドウの基本

