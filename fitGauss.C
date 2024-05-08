#include <TH1F.h>
#include <fstream>
#include <iostream>
#include <TF1.h>

void fitGauss()
{
    // TH1F *h = new TH1F("h", "Histogram", 50, 0.461, 0.4725); // range for amplitude
    TH1F *h = new TH1F("h", "Histogram", 100, 56.7, 57.4); // range for phase

    std::ifstream file("datiLab2/ErroreCasualeFase.txt");
    if (!file)
    {
        std::cerr << "Unable to open file";
        return;
    }
    double value;
    while (file >> value)
    {
        h->Fill(value);
    }
    file.close();

    h->Draw();

    TF1 *fit = new TF1("gaussFit", "gaus(0)");
    // gausn(0) è normalizzata

    std::cout << "media istogramma = " << h->GetMean() << " +/- " << h->GetMeanError() << '\n';
    std::cout << "dev. standard istogramma = " << h->GetRMS() << " +/- " << h->GetRMSError() << '\n';

    h->Fit("gaussFit", "Q");
    std::cout << "ampiezza fit = " << fit->GetParameter(0) << " +/- " << fit->GetParError(0) << '\n';
    std::cout << "media fit = " << fit->GetParameter(1) << " +/- " << fit->GetParError(1) << '\n';
    std::cout << "dev. standard fit = " << fit->GetParameter(2) << " +/- " << fit->GetParError(2) << '\n';
    std::cout << "chi quadro fit = " << fit->GetChisquare() / fit->GetNDF() << '\n';
}