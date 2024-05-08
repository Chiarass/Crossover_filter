#include "TGraphErrors.h"
#include "TF1.h"
#include "TAxis.h"
#include "TStyle.h"
#include "TLegend.h"

void fitLinear()
{
    TGraphErrors *dataAI0 = new TGraphErrors("datiLab2/SistematicaFaseAI0.txt", "%lg %lg");
    TGraphErrors *dataAI1 = new TGraphErrors("datiLab2/SistematicaFaseAI1.txt", "%lg %lg");
    TGraphErrors *dataAI2 = new TGraphErrors("datiLab2/SistematicaFaseAI2.txt", "%lg %lg");

    // Fit linear: [0] = m, [1] = q
    TF1 *fitAI0 = new TF1("f0", "[0]*x + [1]");
    TF1 *fitAI1 = new TF1("f1", "[2]*x + [3]");
    TF1 *fitAI2 = new TF1("f2", "[4]*x + [5]");

    // cosmetics
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetGridColor(kGray);
    dataAI0->GetYaxis()->SetTitle("fase [deg]");
    dataAI0->GetXaxis()->SetTitle("frequenza [Hz]");
    dataAI0->SetMarkerStyle(7);
    dataAI0->SetMarkerColor(kViolet + 6);
    fitAI0->SetLineColor(kViolet);
    fitAI0->SetLineWidth(1);
    dataAI1->SetMarkerStyle(7);
    dataAI1->SetMarkerColor(kAzure + 7);
    fitAI1->SetLineColor(kAzure);
    fitAI1->SetLineWidth(1);
    dataAI2->SetMarkerStyle(7);
    dataAI2->SetMarkerColor(kPink - 2);
    fitAI2->SetLineColor(kRed);
    fitAI2->SetLineWidth(1);

    // fit
    dataAI0->Fit("f0", "Q");
    dataAI1->Fit("f1", "Q");
    dataAI2->Fit("f2", "Q");

    // draw
    dataAI0->Draw("A, P");
    dataAI0->SetTitle("Errore sistematico misure di fase");
    dataAI0->GetYaxis()->SetRangeUser(-2., 20);
    dataAI1->Draw("SAMEPX");
    dataAI2->Draw("SAMEPX");

    // legend
    auto legend = new TLegend(0.85, 0., 1., 0.1);
    legend->AddEntry(dataAI0, "Canale AI0", "lp");
    legend->AddEntry(dataAI1, "Canale AI1", "lp");
    legend->AddEntry(dataAI2, "Canale AI2", "lp");
    legend->Draw();

    // print
    std::cout << "AI0 fit:" << '\n';
    std::cout << "m = " << fitAI0->GetParameter(0) << " +/- " << fitAI0->GetParError(0) << '\n';
    std::cout << "q = " << fitAI0->GetParameter(1) << " +/- " << fitAI0->GetParError(1) << '\n';
    std::cout << "reduced chi-square = " << fitAI0->GetChisquare() / fitAI0->GetNDF() << '\n';
    std::cout << "**********************************\n";
    std::cout << "AI1 fit:" << '\n';
    std::cout << "m = " << fitAI1->GetParameter(2) << " +/- " << fitAI1->GetParError(2) << '\n';
    std::cout << "q = " << fitAI1->GetParameter(3) << " +/- " << fitAI1->GetParError(3) << '\n';
    std::cout << "reduced chi-square = " << fitAI1->GetChisquare() / fitAI1->GetNDF() << '\n';
    std::cout << "**********************************\n";
    std::cout << "AI2 fit:" << '\n';
    std::cout << "m = " << fitAI2->GetParameter(4) << " +/- " << fitAI2->GetParError(4) << '\n';
    std::cout << "q = " << fitAI2->GetParameter(5) << " +/- " << fitAI2->GetParError(5) << '\n';
    std::cout << "reduced chi-square = " << fitAI2->GetChisquare() / fitAI2->GetNDF() << '\n';
}