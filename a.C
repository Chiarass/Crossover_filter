#include "TMath.h"
#include "TF1.h"

void a()
{
    TF1 *fitTweeter = new TF1("fT", "TMath::ATan(1/(x*[0]*[1]))", 8000, 12000);
    fitTweeter->SetParameters(26.1e-9, 560.);
    fitTweeter->Draw();
}