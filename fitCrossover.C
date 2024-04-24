#include "TGraphErrors.h"
#include "TH1F.h"
#include "TF1.h"

void fitCrossover()
{
    TGraphErrors *dataWoofer = new TGraphErrors("datiLab2/SweepAmpiezzaLargoWoofer.txt", "%lg %lg");   // add y errors
    TGraphErrors *dataTweeter = new TGraphErrors("datiLab2/SweepAmpiezzaLargoTweeter.txt", "%lg %lg"); // add y errors

    // Fit woofer: [0] = V0, [1] = R, [2] = L
    TF1 *fitWoofer = new TF1("fW", "[0]*[1]/sqrt([1]^2 + x^2 * [2]^2)");
    fitWoofer->SetParameters(1., 559.9, 10.2e-3);
    dataWoofer->Fit("fW", "Q");

    // Fit tweeter: [0] = V0, [1] = R, [2] = C
    TF1 *fitTweeter = new TF1("f", "[0]*[1]/sqrt([1]^2 + 1/(x^2 * [2]^2))");
    fitTweeter->SetParameters(1., 560., 26.10e-9);
    dataTweeter->Fit("f", "Q");

    // dataWoofer->Draw("A, P");
    dataTweeter->Draw("A, P");
    // fitWoofer->Draw("SAME");
    fitTweeter->Draw("SAME");

    std::cout << "Woofer fit:" << '\n';
    std::cout << "V0 = " << fitWoofer->GetParameter(0) << " +/- " << fitWoofer->GetParError(0) << " Volt" << '\n';
    std::cout << "R = " << fitWoofer->GetParameter(1) << " +/- " << fitWoofer->GetParError(1) << " Ohm" << '\n';
    std::cout << "L = " << fitWoofer->GetParameter(2) << " +/- " << fitWoofer->GetParError(2) << " Henry" << '\n';
    std::cout << "reduced chi-square = " << fitWoofer->GetChisquare() / fitWoofer->GetNDF() << '\n';
    std::cout << "**********************************\n";
    std::cout << "Tweeter fit:" << '\n';
    std::cout << "V0 = " << fitTweeter->GetParameter(0) << " +/- " << fitTweeter->GetParError(0) << " Volt" << '\n';
    std::cout << "R = " << fitTweeter->GetParameter(1) << " +/- " << fitTweeter->GetParError(1) << " Ohm" << '\n';
    std::cout << "C = " << fitTweeter->GetParameter(2) << " +/- " << fitTweeter->GetParError(2) << " Farad" << '\n';
    std::cout << "reduced chi-square = " << fitTweeter->GetChisquare() / fitTweeter->GetNDF() << '\n';
}
