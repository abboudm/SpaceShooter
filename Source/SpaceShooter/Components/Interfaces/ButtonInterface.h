#pragma once
#include "ButtonInterface.generated.h"

// Must have blueprint type as specifier to have this exposed to blueprints
UINTERFACE(BlueprintType)
class SPACESHOOTER_API UButtonInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class SPACESHOOTER_API IButtonInterface
{
	GENERATED_IINTERFACE_BODY()


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Buttons")
		bool RecieveButtonMsg(int channel);


};
