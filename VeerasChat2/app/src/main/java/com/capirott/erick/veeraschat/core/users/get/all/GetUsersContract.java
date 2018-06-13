package com.capirott.erick.veeraschat.core.users.get.all;

import com.capirott.erick.veeraschat.models.User;

import java.util.List;



public interface GetUsersContract {
    interface View {
        void onGetAllUsersSuccess(List<User> users);

        void onGetAllUsersFailure(String message);

    }

    interface Presenter {
        void getAllUsers();

    }

    interface Interactor {
        void getAllUsersFromFirebase();
    }

    interface OnGetAllUsersListener {
        void onGetAllUsersSuccess(List<User> users);

        void onGetAllUsersFailure(String message);
    }

}
