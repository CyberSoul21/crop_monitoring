import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { RecomendationsPageRoutingModule } from './recomendations-routing.module';

import { RecomendationsPage } from './recomendations.page';

import { ComponentsModule } from '../../components/components.module';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    RecomendationsPageRoutingModule,
    ComponentsModule
  ],
  declarations: [RecomendationsPage]
})
export class RecomendationsPageModule {}
