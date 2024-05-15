#include "TGraphErrors.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"
#include "TStyle.h"
#include "TLegend.h"

void fitCrossoverPhase()
{
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetGridColor(kGray);
    // gStyle->SetOptFit(0111);

    TGraphErrors *dataWoofer = new TGraphErrors("datiLab2/SweepFaseWooferCorretto.txt", "%lg %lg %lg");
    TGraphErrors *dataTweeter = new TGraphErrors("datiLab2/SweepFaseTweeterCorretto.txt", "%lg %lg %lg");

    // Fit woofer: [0] = L, [1] = R
    TF1 *fitWoofer = new TF1("fW", "360/(2 * TMath::Pi()) * - TMath::ATan(2*TMath::Pi()*x*[0]/[1])", 8000, 12000);
    // remove the minus in the formula when fitting abs woofer phase
    fitWoofer->SetParameters(10.2e-3, 559.9);
    fitWoofer->SetParLimits(0, 9.e-3, 11.e-3);
    fitWoofer->SetParLimits(1, 500., 570.);

    // Fit tweeter: [0] = C, [1] = R
    TF1 *fitTweeter = new TF1("fT", "360/(2 * TMath::Pi()) * TMath::ATan(1/(2*TMath::Pi()*x*[0]*[1]))", 8000, 12000);
    fitTweeter->SetParameters(26.1e-9, 560.);
    fitTweeter->SetParLimits(0, 20.e-9, 40.e-9);
    fitTweeter->SetParLimits(1, 530., 800.);

    // cosmetics
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetGridColor(kGray);
    dataWoofer->SetTitle(" ");
    dataWoofer->GetYaxis()->SetRangeUser(-80, 80);
    dataWoofer->GetYaxis()->SetTitle("fase [deg]");
    dataWoofer->GetXaxis()->SetTitle("frequenza [Hz]");
    dataWoofer->SetMarkerStyle(7);
    dataWoofer->SetMarkerColor(kOrange - 3);
    fitWoofer->SetLineColor(kOrange);
    fitWoofer->SetLineWidth(1);
    dataTweeter->SetMarkerStyle(7);
    dataTweeter->SetMarkerColor(kTeal + 4);
    fitTweeter->SetLineColor(kTeal);
    fitTweeter->SetLineWidth(1);

    // fit
    dataWoofer->Fit("fW", "Q");
    dataTweeter->Fit("fT", "Q");

    dataWoofer->Draw("APX");
    dataTweeter->Draw("SAMEPX");
    // fitWoofer->Draw("SAME");
    // fitTweeter->Draw("SAME");

    auto legend = new TLegend(0.85, 0., 1., 0.1);
    legend->AddEntry(dataWoofer, "Dati woofer", "lpe");
    legend->AddEntry(dataTweeter, "Dati tweeter", "lpe");
    legend->Draw();

    std::cout << "Woofer phase fit:" << '\n';
    std::cout << "L = " << fitWoofer->GetParameter(0) << " +/- " << fitWoofer->GetParError(0) << " Henry" << '\n';
    std::cout << "R = " << fitWoofer->GetParameter(1) << " +/- " << fitWoofer->GetParError(1) << " Ohm" << '\n';
    std::cout << "reduced chi-square = " << fitWoofer->GetChisquare() / fitWoofer->GetNDF() << '\n';
    std::cout << "**********************************\n";
    std::cout << "Tweeter phase fit:" << '\n';
    std::cout << "C = " << fitTweeter->GetParameter(0) << " +/- " << fitTweeter->GetParError(0) << " Farad" << '\n';
    std::cout << "R = " << fitTweeter->GetParameter(1) << " +/- " << fitTweeter->GetParError(1) << " Ohm" << '\n';
    std::cout << "reduced chi-square = " << fitTweeter->GetChisquare() / fitTweeter->GetNDF() << '\n';
}