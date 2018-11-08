import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams, ToastController } from 'ionic-angular';
import { Account } from '../../models/account';
import { AuthProvider } from '../../providers/auth/auth';

/**
 * Generated class for the LoginPage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */

@IonicPage()
@Component({
  selector: 'page-login',
  templateUrl: 'login.html',
})
export class LoginPage {

  private account: Account;

  constructor(public navCtrl: NavController, public navParams: NavParams, private auth: AuthProvider, private toast: ToastController) {
    this.account = { email: '', password: '' };
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad LoginPage');
  }

  navigateTo(page: string) {
    this.navCtrl.push(page);
  }

  async login () {
    if (this.validate()) {
      try {
        await this.auth.loginWithEmailAndPassword(this.account);
        this.navCtrl.setRoot('HomePage');
      } catch (e) {
        this.toast.create({ duration: 3000, message: e.message }).present();
      }
    } else {
      this.toast.create({ duration: 3000, message: "Empty fields not allowed." }).present();
    }

  }

  validate() {
    return (this.account.email != "" && this.account.password != "")
  }
}
