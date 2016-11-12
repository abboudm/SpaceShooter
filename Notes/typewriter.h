


EDialogueState
{
  Speaking,
  Idle,

};

float TypeWriterSpeed = 0.5
int TypeWriterIndex = 0;
FString ResponseString;


void SpeakResponse()
{
  if(valid ResponseString)
  {
    SetState(Speaking);
    ResponseString = "";
    TypewriterIndex = 0;
    FTimer(TypeWriterSpeed, &TypeResponseString(Topic->ResponseText));
  }
}


void TypeResponseString(FString fullstring)
{
  if (fullstring != responsestring)
  {

    ResponseString += fullstring.getchar(TypewriterIndex);

    TypeWriterIndex++;

    FTimer(TypeWriterSpeed, &TypeResponseString(Topic->ResponseText));

  }
  else
  {
    SetState(Idle);
  }

}
