/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "EdGraphSchema_K2.h"
#include "NpcBehaviorGraphSchema.generated.h"

class UEdGraph;
class UNpcBehaviorTask_Default;
class UNpcBehaviorGraphNode;

/************************************************************************/
/* FNpcBehaviorGraphSchemaAction_NewTask                                */
/************************************************************************/

/** Action to add a task node to the graph */
USTRUCT()
struct UT_FRAMEWORKEDITOR_API FNpcBehaviorGraphSchemaAction_NewTask : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	FName TaskName;
	
	/************************************************************************/
	/* FUNCTIONS                                                            */
	/************************************************************************/

	FNpcBehaviorGraphSchemaAction_NewTask()
		: FEdGraphSchemaAction()
	{}

	FNpcBehaviorGraphSchemaAction_NewTask(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, FName InTask)
		: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
	{
		this->TaskName = InTask;
	}

	//~ Begin FEdGraphSchemaAction Interface
	virtual FName GetTypeId() const override { return StaticGetTypeId(); }
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	//~ End FEdGraphSchemaAction Interface

	// Simple type info
	static FName StaticGetTypeId() { static FName Type("FNpcBehaviorGraphSchemaAction_NewTask"); return Type; }

};

/************************************************************************/
/* UNpcBehaviorGraphSchema				                                */
/************************************************************************/

/**
 *
 */
UCLASS()
class UT_FRAMEWORKEDITOR_API UNpcBehaviorGraphSchema : public UEdGraphSchema_K2
{
	GENERATED_UCLASS_BODY()

public:

	/** Check whether connecting these pins would cause a loop */
	bool ConnectionCausesLoop(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const;

	/** Get menu for breaking links to specific nodes*/
	void GetBreakLinkToSubMenuActions(class FMenuBuilder& MenuBuilder, class UEdGraphPin* InGraphPin);

 	//~ Begin EdGraphSchema Interface
 	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override;
	virtual bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;
	virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;
	virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;
	virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;
	virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;
 	//~ End EdGraphSchema Interface
};
