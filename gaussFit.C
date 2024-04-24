#include <TGraph.h>
#include <TH1F.h>

void gaussFit()
{
    TGraph *data = new TGraph("datiLab2/ErroreAmpiezze.txt");
    data->Draw();
}