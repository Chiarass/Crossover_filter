#include <TH1F.h>
#include <fstream>
#include <iostream>
#include <TF1.h>

void gaussFit()
{
    TH1F *h = new TH1F("h", "Histogram", 50000, 0.46, 0.475); // adjust bins and range as needed

    std::ifstream file("datiLab2/ErroreAmpiezze.txt");
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