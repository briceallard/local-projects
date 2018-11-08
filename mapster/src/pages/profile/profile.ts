import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams, ToastController } from 'ionic-angular';
import { DataProvider } from '../../providers/data/data';
import { User } from '../../models/profile.interface';
import { AuthProvider } from '../../providers/auth/auth';

/**
 * Generated class for the ProfilePage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */

@IonicPage()
@Component({
  selector: 'page-profile',
  templateUrl: 'profile.html',
})
export class ProfilePage {

  private profile: User;

  constructor(public navCtrl: NavController, public navParams: NavParams, private data: DataProvider, private auth: AuthProvider, private toast: ToastController) {
    auth.getAuthenticatedUser()
      .then((user) => { this.profile = { fName: '', lName: '', email: user.email } })

  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad ProfilePage');
  }

  async createProfile() {
    if (this.validate()) {
      try {
        await this.data.createProfile(this.profile);
      } catch (e) {
        this.toast.create({ duration: 3000, message: e.message }).present();
      }
    } else {
      this.toast.create({ duration: 3000, message: "Empty Fields not Allowed" }).present();
    }
  }

  validate() {
    return this.profile.fName != '' && this.profile.lName != '';
  }
}
