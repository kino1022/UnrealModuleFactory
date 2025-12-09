# GAS (Gameplay Ability System) 使用方法ガイド

## 📋 システム概要

このプロジェクトでは、**2つのDataAsset**を使用してInputActionとGameplayAbilityを結びつけます。

### システムフロー
```
プレイヤー入力 (キー/ボタン)
    ↓
[1] AbilityInputConfig で InputAction → InputTag に変換
    ↓
InputTag (例: Input.Action.Jump)
    ↓
ActionAbilitySystemComponent::ProcessAbilityInput
    ↓
[2] StartTag と一致するアビリティを検索
    ↓
アビリティ起動！
```

---

## 🔧 セットアップ手順

### ステップ1: GameplayTagの作成

`Config/DefaultGameplayTags.ini` または エディタで以下のタグを作成：

```ini
[/Script/GameplayTags.GameplayTagsList]
+GameplayTagList=(Tag="Input.Action.Jump",DevComment="ジャンプ入力")
+GameplayTagList=(Tag="Input.Action.Sprint",DevComment="スプリント入力")
+GameplayTagList=(Tag="Input.Action.Attack",DevComment="攻撃入力")
```

---

### ステップ2: アビリティクラスの作成

#### C++の場合
```cpp
// GA_Jump.h
#pragma once
#include "Action/ActionAbility.h"
#include "GA_Jump.generated.h"

UCLASS()
class UGA_Jump : public UActionAbility
{
    GENERATED_BODY()
    
public:
    UGA_Jump();
    
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                 const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                 const FGameplayEventData* TriggerEventData) override;
};

// GA_Jump.cpp
#include "GA_Jump.h"
#include "GameFramework/Character.h"

UGA_Jump::UGA_Jump()
{
    // StartTagを設定（このタグでアビリティが起動される）
    StartTag = FGameplayTag::RequestGameplayTag(FName("Input.Action.Jump"));
}

void UGA_Jump::ActivateAbility(...)
{
    if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
    {
        Character->Jump();
    }
    
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
```

#### Blueprintの場合
1. `Content Browser` → 右クリック → `Blueprint Class`
2. 親クラスを `ActionAbility` に設定
3. `Class Defaults` で `Start Tag` を設定（例: `Input.Action.Jump`）
4. `Activate Ability` イベントをオーバーライドして実装

---

### ステップ3: ActionAbilitySet DataAssetの作成

1. **Content Browserで右クリック**
2. `Miscellaneous` → `Data Asset`
3. クラスを `ActionAbilitySet` に設定
4. 名前を `DA_PlayerAbilitySet` などに変更

#### 設定内容
```
Abilities:
  [0]
    Ability Class: GA_Jump (または BP_GA_Jump)
    Level: 1
    Input Tag: Input.Action.Jump
  [1]
    Ability Class: GA_Sprint
    Level: 1
    Input Tag: Input.Action.Sprint
  [2]
    Ability Class: GA_Attack
    Level: 1
    Input Tag: Input.Action.Attack
```

**重要:** `Input Tag` は各アビリティの `Start Tag` と**完全一致**させてください。

---

### ステップ4: AbilityInputConfig DataAssetの作成

1. **Content Browserで右クリック**
2. `Miscellaneous` → `Data Asset`
3. クラスを `AbilityInputConfig` に設定
4. 名前を `DA_PlayerInputConfig` などに変更

#### 設定内容
```
Ability Input Actions:
  [0]
    Input Action: IA_Jump (Enhanced Input Action)
    Input Tag: Input.Action.Jump
  [1]
    Input Action: IA_Sprint
    Input Tag: Input.Action.Sprint
  [2]
    Input Action: IA_Attack
    Input Tag: Input.Action.Attack
```

---

### ステップ5: キャラクターBlueprintの設定

1. **BP_PlayerCharacter** を開く
2. **ActionAbilitySystemComponent** の設定:
   - `Default Ability Set` → `DA_PlayerAbilitySet` を設定
3. **キャラクターのClass Defaults**:
   - `Ability Input Config` → `DA_PlayerInputConfig` を設定

---

### ステップ6: 初期化処理の確認

`CharacterBase::PossessedBy` で自動的に以下が実行されます：

```cpp
void ACharacterBase::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    
    if (NewController && AbilitySystemComponent)
    {
        // 1. ASCの初期化
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
        
        // 2. アトリビュートの初期化
        InitializeAttribute();
        
        // 3. アビリティの付与（ActionAbilitySetから）
        if (UActionAbilitySystemComponent* ActionASC = Cast<UActionAbilitySystemComponent>(AbilitySystemComponent))
        {
            ActionASC->InitializeAbilities();
        }
    }
}
```

**追加の設定は不要です！**

---

## 🎮 実行時の動作

### 1. プレイヤーが「スペースキー」を押す
↓
### 2. Enhanced Input が `IA_Jump` をトリガー
↓
### 3. `AbilityInputConfig` で `Input.Action.Jump` に変換
↓
### 4. `CharacterBase::Input_AbilityInputTagPressed` が呼ばれる
↓
### 5. `ActionAbilitySystemComponent::AbilityInputStarted` が呼ばれる
↓
### 6. `ProcessAbilityInput` で `StartTag == Input.Action.Jump` のアビリティを検索
↓
### 7. `GA_Jump` が見つかり、`TryActivateAbility` が呼ばれる
↓
### 8. アビリティが実行される！

---

## 🔍 デバッグ方法

### ログ出力の確認
`Output Log` で以下のメッセージを確認：

```
LogTemp: InitializeAbilities: Granting 3 abilities from AbilitySet
LogTemp:   - Granted ability: GA_Jump (Level 1, InputTag: Input.Action.Jump)
LogTemp:   - Granted ability: GA_Sprint (Level 1, InputTag: Input.Action.Sprint)
LogTemp:   - Granted ability: GA_Attack (Level 1, InputTag: Input.Action.Attack)
LogTemp: InitializeAbilities: Complete for BP_PlayerCharacter_C_0
```

### コンソールコマンド
ゲーム実行中に `~` キーでコンソールを開き：

```
showdebug abilitysystem
```

付与されているアビリティ一覧が表示されます。

---

## ⚠️ よくある問題と解決方法

### 問題1: アビリティが起動しない
**チェック項目:**
- ✅ `ActionAbilitySet` の `Input Tag` と アビリティの `Start Tag` が一致しているか
- ✅ `AbilityInputConfig` の `Input Tag` が上記と一致しているか
- ✅ `InitializeAbilities()` が呼ばれているか（ログ確認）
- ✅ Enhanced Input Mapping Context が適用されているか

### 問題2: アビリティが重複して付与される
**原因:** `InitializeAbilities()` が複数回呼ばれている
**解決策:** 実装済みの重複防止機構（`bAbilitiesInitialized`）が動作しているか確認

### 問題3: クライアントでアビリティが動かない
**原因:** マルチプレイヤーでのレプリケーション設定
**解決策:** `OnRep_PlayerState` で `InitAbilityActorInfo` が呼ばれているか確認（クライアント側）

---

## 📚 アビリティの拡張例

### レベルベースのダメージ
```cpp
UCLASS()
class UGA_Attack : public UActionAbility
{
    GENERATED_BODY()
    
public:
    UPROPERTY(EditDefaultsOnly, Category = "Ability")
    float BaseDamage = 10.0f;
    
    virtual void ActivateAbility(...) override
    {
        // レベルに応じてダメージを増加
        float Damage = BaseDamage * GetAbilityLevel();
        
        // ダメージ処理...
        
        EndAbility(...);
    }
};
```

ActionAbilitySetで `Level: 3` に設定すれば、ダメージは `30.0` になります。

---

## 🎯 まとめ

| DataAsset | 役割 | 設定内容 |
|-----------|------|----------|
| **AbilityInputConfig** | 入力→タグ | InputAction → InputTag |
| **ActionAbilitySet** | タグ→アビリティ | InputTag → AbilityClass + Level |

両方を設定することで、柔軟で保守性の高いGASシステムが構築できます！

