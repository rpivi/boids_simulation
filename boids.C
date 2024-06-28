void setStyle(){
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void grafico(){

    // Instance of the graph
    TGraphErrors * p =new TGraphErrors("position.dat", "%lg%lg%lg%lg");
    //x,y,xerr,yerr 

    // Cosmetics
    p->SetMarkerStyle(kOpenCircle);
    p->SetMarkerColor(kBlack);
    p->SetLineColor(kBlue);

    // The canvas on which we'll draw the graph
    TCanvas *canvas_p = new TCanvas("canvas_p","Posizioni",1000,1000);
    p->Draw("APE");

    canvas_p->Print("Posizioni.gif");
}