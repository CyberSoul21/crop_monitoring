import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { RecomendationsPage } from './recomendations.page';

const routes: Routes = [
  {
    path: '',
    component: RecomendationsPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class RecomendationsPageRoutingModule {}
