package com.capirott.erick.veeraschat.ui.activities;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import com.capirott.erick.veeraschat.FirebaseChatMainApp;
import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.core.friend.add.AddFriendContract;
import com.capirott.erick.veeraschat.core.friend.add.AddFriendPresenter;
import com.capirott.erick.veeraschat.models.User;
import com.capirott.erick.veeraschat.ui.fragments.ChatFragment;
import com.capirott.erick.veeraschat.utils.Constants;

public class ChatActivity extends AppCompatActivity implements AddFriendContract.View {

    private Toolbar mToolbar;

    private AddFriendPresenter mAddFriendPresenter;

    private User user;

    public static void startActivity(Context context, User user) {
        Intent intent = new Intent(context, ChatActivity.class);
        intent.putExtra(Constants.ARG_USER_RECEIVER, user);
        context.startActivity(intent);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_add_friend:
                addFriend();
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    private void addFriend() {
        new AlertDialog.Builder(this)
                .setTitle(R.string.new_friend)
                .setMessage(R.string.are_you_sure)
                .setPositiveButton(R.string.add_friend, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                        Log.d("ChatActivity", "addFriend: " + user.getNickname());
//                        mAddFriendPresenter.addFriend();
                    }
                })
                .setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                })
                .show();


//        Toast.makeText(this, "Friend Added!", Toast.LENGTH_SHORT).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_chat_listing, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        user = (User) getIntent().getSerializableExtra(Constants.ARG_USER_RECEIVER);
        setContentView(R.layout.activity_chat);
        bindViews();
        init();
    }

    private void bindViews() {
        mToolbar = (Toolbar) findViewById(R.id.toolbar);
    }

    private void init() {
        // set the toolbar
        setSupportActionBar(mToolbar);

        mAddFriendPresenter = new AddFriendPresenter(this);

        // set toolbar title
        mToolbar.setTitle(user.getNickname());

        // set the register screen fragment
        FragmentTransaction fragmentTransaction = getSupportFragmentManager().beginTransaction();
        fragmentTransaction.replace(R.id.frame_layout_content_chat,
                ChatFragment.newInstance(user), ChatFragment.class.getSimpleName());
        fragmentTransaction.commit();
    }

    @Override
    protected void onResume() {
        super.onResume();
        FirebaseChatMainApp.setChatActivityOpen(true);
    }

    @Override
    protected void onPause() {
        super.onPause();
        FirebaseChatMainApp.setChatActivityOpen(false);
    }

    @Override
    public void onAddFriendSuccess(String message) {

    }

    @Override
    public void onAddFriendFailure(String message) {

    }
}
