# SprintActionAbility セットアップガイド

## 概要
SprintActionAbilityは、スタミナを消費しながらスプリント機能を提供するGameplayAbilityです。
スタミナが0になると自動的にアビリティが終了します。

## 実装内容

### 1. スタミナ監視システム
- 定期的にスタミナ値をチェック（デフォルト: 0.1秒ごと）
- スタミナが0以下になったらアビリティを自動終了
- アビリティ開始時にもスタミナをチェック（スタミナがない場合は実行不可）

### 2. スタミナ消費
- 継続的にスタミナを消費するGameplayEffectを適用
- StaminaDrainEffectとStaminaDrainRateで消費量を制御

## セットアップ手順

### ステップ1: スタミナ消費用のGameplayEffectを作成

1. Content Browserで右クリック → `Gameplay` → `Gameplay Effect`
2. 名前を `GE_StaminaDrain` として作成
3. 以下の設定を行う:

#### Duration Policy
- `Infinite` に設定（継続的に効果を適用）

#### Period
- `Has Period` にチェック
- `Period` を `1.0` に設定（1秒ごとに実行）
- `Execute Periodic Effect on Application` にチェック（適用時にも即座に実行）

#### Modifiers
- 新しいModifierを追加
- `Attribute`: `StaminaAttributeSet.Stamina`
- `Modifier Op`: `Add`
- `Modifier Magnitude`:
  - `Magnitude Calculation Type`: `Set By Caller`
  - `Data Tag`: `Data.Stamina`（この値は負の値として渡される）

### ステップ2: スプリント速度上昇用のGameplayEffectを作成

1. Content Browserで右クリック → `Gameplay` → `Gameplay Effect`
2. 名前を `GE_SprintEffect` として作成
3. 以下の設定を行う:

#### Duration Policy
- `Infinite` に設定

#### Modifiers
- 新しいModifierを追加
- `Attribute`: 移動速度のAttribute（例: `CharacterMovementComponent.MaxWalkSpeed`）
- `Modifier Op`: `Multiply`
- `Modifier Magnitude`:
  - `Magnitude Calculation Type`: `Set By Caller`
  - `Data Tag`: SprintTag（SprintActionAbilityで設定したタグ）

### ステップ3: SprintActionAbilityブループリントを作成

1. Content Browserで右クリック → `Blueprint Class`
2. 親クラスを `SprintActionAbility` として選択
3. 名前を `BP_SprintActionAbility` として作成
4. 以下のプロパティを設定:

#### SprintActionAbility設定
- `Sprint Rate`: `1.5`（1.5倍速になる）
- `Sprint Effect`: 作成した `GE_SprintEffect` を選択
- `Stamina Drain Effect`: 作成した `GE_StaminaDrain` を選択
- `Stamina Drain Rate`: `10.0`（秒間10スタミナ消費）
- `Stamina Check Interval`: `0.1`（0.1秒ごとにチェック）
- `Sprint Tag`: `Data.Sprint` などの適切なGameplayTagを設定

#### ActionAbility基本設定
- `Ability Tags`: アビリティを識別するタグを追加
- `Start Tag`: InputActionに対応するタグ（例: `Input.Action.Sprint`）
- `Activation Owned Tags`: アビリティがアクティブな間付与されるタグ
- `Cancel Abilities with Tag`: 競合するアビリティのタグ

### ステップ4: ActionAbilitySystemComponentにアビリティを登録

#### 方法A: AbilityInputConfigを使用（推奨）

1. AbilityInputConfigデータアセットを開く
2. `Abilities`配列に新しいエントリを追加:
   - `Input Tag`: `Input.Action.Sprint`
   - `Ability Class`: `BP_SprintActionAbility`
   - `Level`: `1`

3. CharacterのBeginPlayまたは適切なタイミングで:
```cpp
// ActionAbilitySystemComponentの初期化
if (UActionAbilitySystemComponent* ActionASC = Cast<UActionAbilitySystemComponent>(AbilitySystemComponent))
{
    if (AbilityInputConfig)
    {
        ActionASC->AddAbilitiesFromConfig(AbilityInputConfig);
    }
}
```

#### 方法B: プログラムで直接登録

```cpp
void AYourCharacter::GiveAbilities()
{
    if (HasAuthority() && AbilitySystemComponent)
    {
        // スプリントアビリティを付与
        FGameplayAbilitySpec AbilitySpec(
            BP_SprintActionAbility.GetDefaultObject(),
            1,  // Level
            INDEX_NONE,
            this
        );
        
        AbilitySystemComponent->GiveAbility(AbilitySpec);
    }
}
```

### ステップ5: 入力バインディング

Enhanced Input SystemとActionAbilitySystemComponentが連携している場合、
InputTagに対応した入力が自動的にアビリティをトリガーします。

InputActionのトリガー時に:
- `Started`: InputPressedが呼ばれ、ActivateAbilityが実行される
- `Completed` または `Canceled`: InputReleasedが呼ばれ、EndAbilityが実行される

## 動作の流れ

1. **入力開始時**:
   - InputPressed → ActivateAbility
   - スタミナをチェック（0以下なら即座に終了）
   - SprintEffectを適用（移動速度上昇）
   - StaminaDrainEffectを適用（スタミナ消費開始）
   - スタミナチェックタイマー開始

2. **実行中**:
   - 0.1秒ごとにCheckStaminaが呼ばれる
   - StaminaDrainEffectにより1秒ごとにスタミナが減少
   - スタミナが0以下になったら自動的にCancelAbility

3. **入力終了時** or **スタミナ切れ**:
   - InputReleased or CancelAbility → EndAbility
   - タイマーをクリア
   - SprintEffectを削除（移動速度を元に戻す）
   - StaminaDrainEffectを削除（スタミナ消費停止）

## カスタマイズ

### スタミナ消費量の調整
- `Stamina Drain Rate`: より大きい値 = より速くスタミナが減少
- `Stamina Check Interval`: より小さい値 = より正確なチェック（CPUコストは増加）

### スプリント速度の調整
- `Sprint Rate`: 1.5 = 1.5倍速、2.0 = 2倍速

### スタミナ回復
別のGameplayEffectを作成してスタミナを回復させることができます:
- Duration Policy: `Infinite`
- Period: `1.0`（1秒ごと）
- Modifier: `Add` で正の値を設定
- スプリント中は無効化するためのタグを使用

## トラブルシューティング

### スタミナが減らない
- StaminaDrainEffectが正しく設定されているか確認
- Data.Staminaタグが正しいか確認
- StaminaDrainRateが負の値として渡されているか確認（コード内で-StaminaDrainRate）

### スプリント速度が変わらない
- SprintEffectが正しく設定されているか確認
- SprintTagが一致しているか確認
- Attributeが正しい移動速度Attributeを指しているか確認

### アビリティが終了しない
- StaminaCheckTimerHandleが正しく設定されているか確認
- CheckStamina関数が呼ばれているかログで確認
- StaminaAttributeSetが正しく取得できているか確認

