package com.capirott.erick.veeraschat.core.users.add;

import android.content.Context;

import com.capirott.erick.veeraschat.models.User;


public class AddUserPresenter implements AddUserContract.Presenter, AddUserContract.OnUserDatabaseListener {
        private AddUserContract.View mView;
    private AddUserInteractor mAddUserInteractor;

    public AddUserPresenter(AddUserContract.View view) {
        this.mView = view;
        mAddUserInteractor = new AddUserInteractor(this);
    }

    @Override
    public void addUser(Context context, User user) {
        mAddUserInteractor.addUserToDatabase(context, user);
    }

    @Override
    public void onSuccess(String message) {
        mView.onAddUserSuccess(message);
    }

    @Override
    public void onFailure(String message) {
        mView.onAddUserFailure(message);
    }
}
