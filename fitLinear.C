#include "TGraphErrors.h"
#include "TF1.h"

void fitLinear()
{
    TGraphErrors *dataAI0 = new TGraphErrors("datiLab2/SistematicaFaseAI0.txt", "%lg %lg");
    TGraphErrors *dataAI1 = new TGraphErrors("datiLab2/SistematicaFaseAI1.txt", "%lg %lg");
    TGraphErrors *dataAI2 = new TGraphErrors("datiLab2/SistematicaFaseAI2.txt", "%lg %lg");

    // Fit linear: [0] = m, [1] = q
    TF1 *fitAI0 = new TF1("f0", "[0]*x + [1]");
    TF1 *fitAI1 = new TF1("f1", "[2]*x + [3]");
    TF1 *fitAI2 = new TF1("f2", "[4]*x + [5]");

    dataAI0->Fit("f0", "Q");
    dataAI1->Fit("f1", "Q");
    dataAI2->Fit("f2", "Q");

    dataAI0->Draw("A, P");
    // dataAI0->GetYaxis()->SetRangeUser(-0.5, 0.5);
    // fitAI0->Draw("SAME");
    dataAI1->Draw("SAME");
    // fitAI1->Draw("SAME");
    dataAI2->Draw("SAME");
    // fitAI2->Draw("SAME");

    std::cout << "AI0 fit:" << '\n';
    std::cout << "m = " << fitAI0->GetParameter(0) << " +/- " << fitAI0->GetParError(0) << '\n';
    std::cout << "q = " << fitAI0->GetParameter(1) << " +/- " << fitAI0->GetParError(1) << '\n';
    std::cout << "reduced chi-square = " << fitAI0->GetChisquare() / fitAI0->GetNDF() << '\n';
    std::cout << "**********************************\n";
    std::cout << "AI1 fit:" << '\n';
    std::cout << "m = " << fitAI1->GetParameter(0) << " +/- " << fitAI1->GetParError(0) << '\n';
    std::cout << "q = " << fitAI1->GetParameter(1) << " +/- " << fitAI1->GetParError(1) << '\n';
    std::cout << "reduced chi-square = " << fitAI1->GetChisquare() / fitAI1->GetNDF() << '\n';
    std::cout << "**********************************\n";
    std::cout << "AI2 fit:" << '\n';
    std::cout << "m = " << fitAI2->GetParameter(0) << " +/- " << fitAI2->GetParError(0) << '\n';
    std::cout << "q = " << fitAI2->GetParameter(1) << " +/- " << fitAI2->GetParError(1) << '\n';
    std::cout << "reduced chi-square = " << fitAI2->GetChisquare() / fitAI2->GetNDF() << '\n';
}