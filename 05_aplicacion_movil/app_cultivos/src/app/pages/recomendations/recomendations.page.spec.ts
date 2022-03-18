import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { IonicModule } from '@ionic/angular';

import { RecomendationsPage } from './recomendations.page';

describe('RecomendationsPage', () => {
  let component: RecomendationsPage;
  let fixture: ComponentFixture<RecomendationsPage>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ RecomendationsPage ],
      imports: [IonicModule.forRoot()]
    }).compileComponents();

    fixture = TestBed.createComponent(RecomendationsPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
