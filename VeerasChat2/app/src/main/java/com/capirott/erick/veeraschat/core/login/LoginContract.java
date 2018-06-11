package com.capirott.erick.veeraschat.core.login;

import android.app.Activity;



public interface LoginContract {
    interface View {
        void onLoginSuccess(String message);

        void onLoginFailure(String message);
    }

    interface Presenter {
        void login(Activity activity, String email, String password);
        void loginAnonymously(Activity activity);
    }

    interface Interactor {
        void performFirebaseAnonymouslyLogin(Activity activity);

        void performFirebaseLogin(Activity activity, String email, String password);
    }

    interface OnLoginListener {
        void onSuccess(String message);

        void onFailure(String message);
    }
}
