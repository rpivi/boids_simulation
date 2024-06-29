void setStyle(){
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void boids(){

    // Instance of the graph
    TGraphErrors * px =new TGraphErrors("positionx.dat", "%lg%lg%*lg%lg");
    TGraphErrors * py =new TGraphErrors("positiony.dat", "%lg%lg%*lg%lg");
    TGraphErrors * vx =new TGraphErrors("velocityx.dat", "%lg%lg%*lg%lg");
    TGraphErrors * vy =new TGraphErrors("velocityy.dat", "%lg%lg%*lg%lg");

    // Cosmetics
    px->SetMarkerStyle(kOpenCircle);
    px->SetMarkerColor(kBlack);
    px->SetLineColor(kBlue);

    py->SetMarkerStyle(kOpenCircle);
    py->SetMarkerColor(kBlack);
    py->SetLineColor(kBlue);

    vx->SetMarkerStyle(kOpenCircle);
    vx->SetMarkerColor(kBlack);
    vx->SetLineColor(kRed);

    vy->SetMarkerStyle(kOpenCircle);
    vy->SetMarkerColor(kBlack);
    vy->SetLineColor(kRed);

    // The canvas on which we'll draw the graph
    TCanvas *canvas = new TCanvas("Canvas","Posizioni e Velocità");
    canvas->Divide(2,2);

    canvas->cd(1);
    px->Draw("APE");

    canvas->cd(2);
    py->Draw("APE");

    canvas->cd(3);
    vx->Draw("APE");

    canvas->cd(4);
    vy->Draw("APE");

    canvas_p->Print("Boids.gif");
}